export function main() {
  const myGreeter = new greeter.Greeter("TypeScript");
  console.log(myGreeter.greet(greeter.LanguageCode.EN));
  // manual delete required for JS as there are no destructors
  deleteValue(myGreeter);
  return 0;
}
