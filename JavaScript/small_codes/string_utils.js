function reverse(str) {
  return str.split('').reverse().join('');
}
function isPalindrome(str) {
  const rev = reverse(str);
  return str === rev;
}
console.log(reverse("hello"));
console.log(isPalindrome("madam"));