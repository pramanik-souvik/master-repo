public class StringUtilities {
    public static void main(String[] args) {
        String text = "Hello World!";

        System.out.println("Original: " + text);
        System.out.println("Lowercase: " + text.toLowerCase());
        System.out.println("Uppercase: " + text.toUpperCase());
        System.out.println("Substring(0,5): " + text.substring(0, 5));
        System.out.println("Replace 'World' with 'Java': " + text.replace("World", "Java"));

        String[] words = text.split(" ");
        System.out.println("Split words:");
        for (String word : words) {
            System.out.println(word);
        }

        StringBuilder sb = new StringBuilder();
        sb.append("StringBuilder");
        sb.reverse();
        System.out.println("Reversed with StringBuilder: " + sb);
    }
}