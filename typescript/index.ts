export function main() {
  const myGreeter = new greeter.Greeter("TypeScript");
  console.log(myGreeter.greet(greeter.LanguageCode.EN));
  // we need to manually delete C++ classes as there are no destructors in JavaScript
  deleteValue(myGreeter);
  return 0;
}
