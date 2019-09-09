declare module cpplib {
  /** @customConstructor cpplib.A.__new */
  class A {
    constructor(arg0: number);
    __tostring(): string;
    add(arg1: cpplib.A): cpplib.A;
    data(): number;
    next(): cpplib.A;
    setData(arg1: number): void;
  }
  /** @customConstructor cpplib.B.__new */
  class B extends cpplib.A {
    constructor(arg0: number);
    name(): string;
    setName(arg1: string): void;
  }
  function log(this: void, arg0: string): void;
}

