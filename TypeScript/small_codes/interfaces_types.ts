import * as readline from "readline";

// Interface for a base person
interface Person {
  name: string;
  age: number;
  email?: string; // optional property
}

// Type combining Person + extra properties
type Student = Person & {
  grade: string;
  major: string;
  id: number;
};

// Interface for a course
interface Course {
  code: string;
  title: string;
  credits: number;
}

// Simple database simulation
const students: Student[] = [];
const courses: Course[] = [
  { code: "CS101", title: "Intro to Programming", credits: 3 },
  { code: "MATH201", title: "Calculus II", credits: 4 },
  { code: "ENG110", title: "Creative Writing", credits: 2 },
];

// CLI setup
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

console.log("=== University Enrollment Simulator ===");

function askStudentName() {
  rl.question("Enter student name: ", (name) => {
    rl.question("Enter age: ", (ageStr) => {
      const age = Number(ageStr);
      if (isNaN(age)) {
        console.log("Please enter a valid age.");
        return askStudentName();
      }

      rl.question("Enter grade (A-F): ", (grade) => {
        rl.question("Enter major: ", (major) => {
          const student: Student = {
            name,
            age,
            grade: grade.toUpperCase(),
            major,
            id: students.length + 1,
          };
          students.push(student);
          console.log(`Student enrolled:`, student);
          selectCourse(student);
        });
      });
    });
  });
}

function selectCourse(student: Student) {
  console.log("\nAvailable Courses:");
  courses.forEach((c) => console.log(`  [${c.code}] ${c.title} (${c.credits} credits)`));

  rl.question("\nEnter course code to enroll: ", (code) => {
    const course = courses.find((c) => c.code.toUpperCase() === code.toUpperCase());
    if (!course) {
      console.log("Invalid course code. Try again.");
      return selectCourse(student);
    }

    console.log(
      ` ${student.name} (Grade ${student.grade}) successfully enrolled in "${course.title}"!`
    );

    rl.question("Enroll another student? (yes/no): ", (answer) => {
      if (answer.trim().toLowerCase() === "yes") {
        askStudentName();
      } else {
        console.log("\n=== Final Enrollment Summary ===");
        students.forEach((s) =>
          console.log(`${s.name}, ${s.age} yrs, Grade ${s.grade}, Major: ${s.major}`)
        );
        console.log("All done! Goodbye!");
        rl.close();
      }
    });
  });
}

askStudentName();