// JSON Formatter CLI - Enhanced Version
const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

// Function to format JSON
function formatJSON(jsonStr, pretty = true) {
  try {
    const obj = JSON.parse(jsonStr);
    return pretty ? JSON.stringify(obj, null, 2) : JSON.stringify(obj);
  } catch (e) {
    return `Invalid JSON: ${e.message}`;
  }
}

// Ask user for JSON input
rl.question("Enter JSON string: ", input => {
  rl.question("Do you want pretty print? (yes/no): ", answer => {
    const pretty = answer.trim().toLowerCase() === 'yes';
    const formatted = formatJSON(input, pretty);
    console.log("\nFormatted JSON:\n", formatted);

    // Optional: Save to file
    rl.question("Do you want to save to a file? (yes/no): ", saveAns => {
      if (saveAns.trim().toLowerCase() === 'yes') {
        rl.question("Enter filename: ", filename => {
          fs.writeFileSync(filename, formatted);
          console.log(`Saved formatted JSON to ${filename}`);
          rl.close();
        });
      } else {
        rl.close();
      }
    });
  });
});
