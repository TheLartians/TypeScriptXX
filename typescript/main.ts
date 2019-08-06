
function test() {
  const a = lib.A.create(46);
  const b = lib.B.create(-5);
  b.setName("B");
  console.assert(a.add(b).next().data() == 42);
  console.assert(b.name() == "B");
}

test();

class Greeter {
  private name: string;

  constructor(name: string){
    this.name = name;
  }

  public greet() {
    lib.log(`Hello ${this.name}!`);
  }
}

const greeter = new Greeter("C++");
greeter.greet();
