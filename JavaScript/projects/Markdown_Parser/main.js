// Enhanced Markdown Parser CLI
const fs = require('fs');
const readline = require('readline');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

// Function to parse Markdown to HTML
function parseMarkdown(md) {
  return md
    // Headings
    .replace(/^### (.*$)/gim, '<h3>$1</h3>')
    .replace(/^## (.*$)/gim, '<h2>$1</h2>')
    .replace(/^# (.*$)/gim, '<h1>$1</h1>')
    // Bold and Italic
    .replace(/\*\*(.*?)\*\*/gim, '<b>$1</b>')
    .replace(/\*(.*?)\*/gim, '<i>$1</i>')
    // Inline code
    .replace(/`(.*?)`/gim, '<code>$1</code>')
    // Links
    .replace(/\[([^\]]+)\]\(([^)]+)\)/gim, '<a href="$2">$1</a>')
    // Unordered lists
    .replace(/^\s*-\s+(.*)/gim, '<li>$1</li>')
    // Wrap list items in <ul>
    .replace(/(<li>.*<\/li>)/gims, '<ul>$1</ul>');
}

// Ask user for input
rl.question("Enter markdown text (or type 'file' to load from file): ", input => {
  if (input.trim().toLowerCase() === 'file') {
    rl.question("Enter file path: ", path => {
      try {
        const mdContent = fs.readFileSync(path, 'utf-8');
        const html = parseMarkdown(mdContent);
        console.log("\nParsed HTML:\n", html);
        saveToFile(html);
      } catch (err) {
        console.error("Error reading file:", err.message);
        rl.close();
      }
    });
  } else {
    const html = parseMarkdown(input);
    console.log("\nParsed HTML:\n", html);
    saveToFile(html);
  }
});

// Optional save to file
function saveToFile(html) {
  rl.question("Do you want to save to a file? (yes/no): ", answer => {
    if (answer.trim().toLowerCase() === 'yes') {
      rl.question("Enter output file name: ", filename => {
        fs.writeFileSync(filename, html);
        console.log(`Saved parsed HTML to ${filename}`);
        rl.close();
      });
    } else {
      rl.close();
    }
  });
}