function test() {
  // test bindings
  const a = new glue.lib.A(46);
  const b = new glue.lib.B(-5);
  b.setName("B");
  console.assert(
    a
      .add(b)
      .next()
      .data() == 42
  );
  console.assert(b.name() == "B");
  // test lua lib
  const m = new Map<string, number>();
  m.set("a", 42);
  console.assert(m.get("a") == 42);
  print(`all tests passed`);
}

class Greeter {
  private name: string;

  constructor(name: string) {
    this.name = name;
  }

  public greet() {
    return `Hello ${this.name} from TypeScript!`;
  }
}

export function main() {
  test();
  const greeter = new Greeter("C++");
  glue.lib.log(greeter.greet());
  return 0;
}
