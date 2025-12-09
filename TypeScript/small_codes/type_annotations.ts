// Type Annotations Demo - Profile Analyzer

// Basic typed variables
let personName: string = "Souvik";
let personAge: number = 23;
let is_Student: boolean = true;

// Typed array
let skills: string[] = ["TypeScript", "JavaScript", "Node.js"];

// Typed object
let profile: { name: string; age: number; isStudent: boolean; skills: string[] } = {
  name: personName,
  age: personAge,
  isStudent: is_Student,
  skills,
};

// Typed function
function getProfileSummary(person: { name: string; age: number; isStudent: boolean; skills: string[] }): string {
  const status = person.isStudent ? "a student" : "a professional";
  return `${person.name} is ${person.age} years old and is ${status}. Key skills: ${person.skills.join(", ")}.`;
}

// Typed function returning number
function yearsToRetirement(currentAge: number, retirementAge: number = 60): number {
  return retirementAge - currentAge;
}

// Output
console.log("=== Profile Summary ===");
console.log(getProfileSummary(profile));

console.log("\nYears until retirement:", yearsToRetirement(personAge));