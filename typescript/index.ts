
export function main() {
  const myGreeter = new greeter.Greeter("TypeScript");
  console.log(myGreeter.greet(greeter.LanguageCode.EN));
  return 0;
}
