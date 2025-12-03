import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;

public class Downloader {
    private static final int THREAD_POOL_SIZE = 5;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        List<String> urls = new ArrayList<>();

        System.out.println("--- Multi-Threaded Downloader ---");
        System.out.println("Enter URLs to download (type 'done' to finish):");

        while (true) {
            System.out.print("URL: ");
            String url = sc.nextLine();
            if (url.equalsIgnoreCase("done")) break;
            urls.add(url);
        }

        ExecutorService executor = Executors.newFixedThreadPool(THREAD_POOL_SIZE);

        for (String url : urls) {
            executor.submit(() -> downloadFile(url));
        }

        executor.shutdown();
        try {
            executor.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
            System.out.println("\nAll downloads completed!");
        } catch (InterruptedException e) {
            System.out.println("Download interrupted.");
        }

        sc.close();
    }

    private static void downloadFile(String fileURL) {
        try {
            URL url = new URL(fileURL);
            String fileName = new File(url.getPath()).getName();

            if (fileName.isEmpty()) {
                fileName = "download_" + System.currentTimeMillis();
            }

            System.out.println("Starting download: " + fileName);

            try (InputStream in = url.openStream();
                 FileOutputStream out = new FileOutputStream(fileName)) {

                byte[] buffer = new byte[4096];
                int bytesRead;
                while ((bytesRead = in.read(buffer)) != -1) {
                    out.write(buffer, 0, bytesRead);
                }

                System.out.println("Downloaded: " + fileName);
            }
        } catch (IOException e) {
            System.out.println("Failed to download: " + fileURL + " (" + e.getMessage() + ")");
        }
    }
}