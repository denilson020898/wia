// const importObject = {
//     env: {
//         memory: new WebAssembly.Memory({ initial: 1, maximum: 10 })
//     }
// }

// WebAssembly.instantiateStreaming(fetch("side_module.wasm"), importObject)
//     .then(result => {
//         const value = result.instance.exports._Increment(17);
//         console.log(value.toString());
//     });

// fetch('side_module.wasm')
//     .then(response => 
//         response.arrayBuffer())
//     .then(bytes => 
//         WebAssembly.instantiate(bytes, importObject)
//     ).then(result => {
//         const value = result.instance.exports._Increment(17);
//         console.log(value.toString());
//     });

const importObject = {
    env: {
        __memory_base: 0,
        __table_base: 0,
        memory: new WebAssembly.Memory({initial: 256}),
        table: new WebAssembly.Table({initial: 0, element:'anyfunc'}),
    }
};

WebAssembly.instantiateStreaming(
    fetch("side_module.wasm"),
    importObject
).then(result => {
    const value = result.instance.exports.Increment(17);
    console.log("result is ", value.toString());
});
