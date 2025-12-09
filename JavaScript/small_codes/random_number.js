function randomQuantile() {
  const number = Math.floor(Math.random() * 100) + 1; // 1-100
  let quantile, ratio;

  if (number <= 25) {
    quantile = "1st";
    ratio = "one fourth";
  } else if (number <= 50) {
    quantile = "2nd";
    ratio = "half";
  } else if (number <= 75) {
    quantile = "3rd";
    ratio = "three fourths";
  } else {
    quantile = "4th";
    ratio = "full";
  }

  console.log(`Number  : ${number}`);
  console.log(`Quantile: ${quantile}`);
  console.log(`Ratio   : ${ratio}`);
}

randomQuantile();