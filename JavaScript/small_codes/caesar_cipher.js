// Caesar Cipher: encode and decode
function caesarCipher(str, shift) {
  return str.replace(/[a-z]/gi, char => {
    const base = char <= 'Z' ? 65 : 97; // check uppercase/lowercase
    return String.fromCharCode((char.charCodeAt(0) - base + shift + 26) % 26 + base);
  });
}

function caesarDecipher(str, shift) {
  // decoding is just shifting backwards
  return caesarCipher(str, -shift);
}

// Demo
const encoded = caesarCipher("HELLO world", 3);
console.log("Encoded:", encoded);          // KHOOR zruog

const decoded = caesarDecipher(encoded, 3);
console.log("Decoded:", decoded);          // HELLO world
