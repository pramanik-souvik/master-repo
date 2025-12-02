import java.util.*;

public class Collections {
    public static void main(String[] args) {
        // ArrayList example
        ArrayList<String> list = new ArrayList<>();
        list.add("Apple");
        list.add("Banana");
        list.add("Orange");
        System.out.println("ArrayList: " + list);

        // HashSet example
        Set<Integer> set = new HashSet<>();
        set.add(10);
        set.add(20);
        set.add(10); // duplicate ignored
        System.out.println("HashSet: " + set);

        // HashMap example
        Map<String, Integer> map = new HashMap<>();
        map.put("Alice", 25);
        map.put("Bob", 30);
        System.out.println("HashMap: " + map);

        // Iterating with for-each
        System.out.println("Iterating ArrayList:");
        for (String fruit : list) {
            System.out.println(fruit);
        }
    }
}