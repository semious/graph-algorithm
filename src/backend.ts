import wasmFactory from "../bazel-bin/src/cpp/graph-algo-wasm/graph-algo-wasm.js";

let module;

export async function initWASM(wasmBinary: ArrayBuffer) {
  const wasmModuleConfig: any = {};
  wasmModuleConfig.instantiateWasm = (imports: any, callback: any) => {
    WebAssembly.instantiate(wasmBinary, imports).then((output) => {
      callback(output.instance, output.module);
    });
    return {};
  };
  module = wasmFactory(wasmModuleConfig);
}

export async function calculateRepulsiveForce(){
  // return module.cwrap('calculateRepulsiveForce', null, []);
}

