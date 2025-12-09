function delay(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function runDemo() {
  console.log("Start");
  await delay(1000);
  console.log("After 1 second");
  await delay(9000);
  console.log("After 10 second");
  await delay(10000);
  console.log("After 20 second");
}
runDemo();