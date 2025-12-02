public class ExceptionHandling {
    public static void main(String[] args) {
        try {
            int[] arr = {1, 2, 3};
            System.out.println(arr[5]); // will throw exception
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Caught exception: " + e.getMessage());
        } finally {
            System.out.println("This runs regardless of exception.");
        }

        // Custom exception
        try {
            checkAge(15);
        } catch (Exception e) {
            System.out.println("Custom exception caught: " + e.getMessage());
        }
    }

    static void checkAge(int age) throws Exception {
        if (age < 18) {
            throw new Exception("Age must be 18 or older!");
        }
        System.out.println("Age is valid.");
    }
}
