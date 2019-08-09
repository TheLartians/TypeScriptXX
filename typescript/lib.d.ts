declare module lib {
  /** @customConstructor lib.A.__new */
  class A {
    constructor(arg0: number)
    __tostring(): string;
    add(arg1: lib.A): lib.A;
    data(): number;
    next(): lib.A;
    setData(arg1: number): void;
  }
  /** @customConstructor lib.B.__new */
  class B extends lib.A {
    constructor(arg0: number)
    name(): string;
    setName(arg1: string): void;
  }
  function log(this: void, arg0: string): void;
}

