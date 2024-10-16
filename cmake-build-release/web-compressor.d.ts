// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
declare namespace RuntimeExports {
    let HEAPF32: any;
    let HEAPF64: any;
    let HEAP_DATA_VIEW: any;
    let HEAP8: any;
    let HEAPU8: any;
    let HEAP16: any;
    let HEAPU16: any;
    let HEAP32: any;
    let HEAPU32: any;
    let HEAP64: any;
    let HEAPU64: any;
}
interface WasmModule {
}

type EmbindString = ArrayBuffer|Uint8Array|Uint8ClampedArray|Int8Array|string;
interface EmbindModule {
  toupper(_0: EmbindString): string;
  LZSSCompress(_0: EmbindString, _1: number, _2: number): any;
  LZSSDecompress(_0: EmbindString): any;
  HuffmanCompress(_0: EmbindString): any;
  HuffmanDecompress(_0: EmbindString): any;
  HSCompress(_0: EmbindString, _1: number, _2: number): any;
  HSDecompress(_0: EmbindString): any;
}

export type MainModule = WasmModule & typeof RuntimeExports & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
