let importObject = {
  // imports: {
  //   // imported_func: (arg) => console.log(arg),
  // },
};
fetch("pthreads.wasm")
  .then((res) => res.arrayBuffer())
  .then((bytes) => WebAssembly.instantiate(bytes, importObject))
  .then((results) => {
    // results.instance.exports.exported_func();
  });
