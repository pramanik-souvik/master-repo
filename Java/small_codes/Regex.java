import java.util.regex.*;

public class Regex {
    public static void main(String[] args) {
        String email = "test@example.com";
        String phone = "123-456-7890";

        // Email regex
        Pattern emailPattern = Pattern.compile("^[\\w.-]+@[\\w.-]+\\.\\w+$");
        Matcher emailMatcher = emailPattern.matcher(email);
        System.out.println(email + " is valid email? " + emailMatcher.matches());

        // Phone regex
        Pattern phonePattern = Pattern.compile("^\\d{3}-\\d{3}-\\d{4}$");
        Matcher phoneMatcher = phonePattern.matcher(phone);
        System.out.println(phone + " is valid phone? " + phoneMatcher.matches());
    }
}
