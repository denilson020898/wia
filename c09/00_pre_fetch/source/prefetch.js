let compiledModule = null;
let emscriptenModule = null;

const worker = new Worker("prefetch.worker.js");
worker.onmessage = function(e) {
    compiledModule = e.data;
    Module( {instantiateWasm: onInstantiateWasm }).then((module) => {
        emscriptenModule = module;
    })
}

function onInstantiateWasm(importObject, successCallback) {
    WebAssembly.instantiate(compiledModule, importObject).then(instance =>
        successCallback(instance)
    );
    return {};
}

