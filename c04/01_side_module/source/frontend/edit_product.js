const initialData = {
    name: "Women's Mid Rise Skinny Jeans",
    categoryId: "100"
}

const MAXIMUM_NAME_LENGTH = 50;
const VALID_CATEGORY_IDS = [100, 101];

let moduleMemory = null;
let moduleExports = null;

function validateName(name, errorMessagePointer) {
    const namePointer = moduleExports._create_buffer((name.length + 1));
    copyStringToMemory(name, namePointer);
    const isValid = moduleExports._ValidateName(namePointer, MAXIMUM_NAME_LENGTH,
        errorMessagePointer);
    moduleExports._free_buffer(namePointer);
    return (isValid === 1);
}

function validateCategory(categoryId, errorMessagePointer) {
    const categoryIdPointer = moduleExports._create_buffer((categoryId.length + 1));
    copyStringToMemory(categoryId, categoryIdPointer);

    const arrayLength = VALID_CATEGORY_IDS.length;
    const bytesPerElement = Module.HEAP32.BYTES_PER_ELEMENT;
    const arrayPointer = moduleExports._create_buffer((arrayLength * bytesPerElement));
    const bytesForArray = new Int32Array(moduleMemory.buffer);
    bytesForArray.set(VALID_CATEGORY_IDS, (arrayPointer / bytesPerElement));


    const isValid = moduleExports._ValidateCategory(categoryIdPointer, arrayPointer, 
        arrayLength, errorMessagePointer);

    moduleExports._free_buffer(arrayPointer);
    moduleExports._free_buffer(categoryIdPointer);

    return (isValid === 1);
}

function initializePage() {
    moduleMemory = new WebAssembly.Memory({initial: 256});
    const importObject = {
        env: {
            __memory_base: 0,
            __table_base: 0,
            memory: moduleMemory,
            table: new WebAssembly.Table({initial: 0, element:'anyfunc'}),
        }
    };


    fetch('validate.wasm').then(response =>
        response.arrayBuffer()
    ).then(bytes =>
        WebAssembly.instantiate(bytes, importObject)
    );


    // WebAssembly.instantiateStreaming(fetch("validate.wasm"), importObject)
    //     .then(result => {
    //         console.log("result ->", result);
    //         moduleExports = result.instance.exports;
    //     });

    document.getElementById("name").value = initialData.name;
    const category = document.getElementById("category");
    const count = category.length;
    for (let index = 0; index < count; index++) {
        if (category[index].value === initialData.categoryId) {
            category.selectedIndex = index;
            break;
        }
    }
}

function getSelectedCategoryId() {
    const category = document.getElementById("category");
    const index = category.selectedIndex;
    if (index !== -1) { return category[index].value; }
    return "0";
}

function setErrorMessage(error) {
    const errorMessage = document.getElementById("errorMessage");
    errorMessage.innerText = error;
    errorMessage.style.display = (error === "" ? "none" : "");
}

function onClickSave() {
    let errorMessage = "";
    const errorMessagePointer = moduleExports._create_buffer(256);

    const name = document.getElementById("name").value;
    const categoryId = getSelectedCategoryId();

    if (!validateName(name, errorMessagePointer) ||
        !validateCategory(categoryId, errorMessagePointer)) {
        errorMessage = getStringFromMemory(errorMessagePointer);
    }

    moduleExports._free_buffer(errorMessagePointer);

    setErrorMessage(errorMessage);
    if (errorMessage === "") {
    }
}

function getStringFromMemory(memoryOffset) {
    let returnValue = "";

    const size = 256;
    const bytes = new Uint8Array(moduleMemory.buffer, memoryOffset, size);

    let character = "";
    for (let i = 0; i < size; i++) {
        character = String.fromCharCode(bytes[i]);
        if (character === "\0") { break; }
        returnValue += character;
    }
    return returnValue;
}

function copyStringToMemory(value, memoryOffset) {
    const bytes = new Uint8Array(moduleMemory.buffer);
    bytes.set(new TextEncoder().encode((value + "\0")), memoryOffset);
}

