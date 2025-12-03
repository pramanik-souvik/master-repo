import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;

public class DownloaderGUI extends JFrame {
    private DefaultListModel<String> urlListModel;
    private JList<String> urlList;
    private JButton addButton, removeButton, startButton;
    private JTextField urlField;
    private JPanel progressPanel;
    private ExecutorService executor;

    private static final int THREAD_POOL_SIZE = 5;

    public DownloaderGUI() {
        setTitle("Multi-Threaded Downloader");
        setSize(700, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Top panel for URL input
        JPanel topPanel = new JPanel(new BorderLayout());
        urlField = new JTextField();
        addButton = new JButton("Add URL");
        removeButton = new JButton("Remove Selected");
        JPanel buttonPanel = new JPanel(new GridLayout(1, 2));
        buttonPanel.add(addButton);
        buttonPanel.add(removeButton);
        topPanel.add(urlField, BorderLayout.CENTER);
        topPanel.add(buttonPanel, BorderLayout.EAST);
        add(topPanel, BorderLayout.NORTH);

        // Center panel for URL list
        urlListModel = new DefaultListModel<>();
        urlList = new JList<>(urlListModel);
        urlList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
        add(new JScrollPane(urlList), BorderLayout.CENTER);

        // Bottom panel for start button and progress
        JPanel bottomPanel = new JPanel(new BorderLayout());
        startButton = new JButton("Start Download");
        bottomPanel.add(startButton, BorderLayout.NORTH);

        progressPanel = new JPanel();
        progressPanel.setLayout(new BoxLayout(progressPanel, BoxLayout.Y_AXIS));
        JScrollPane progressScroll = new JScrollPane(progressPanel);
        progressScroll.setPreferredSize(new Dimension(700, 200));
        bottomPanel.add(progressScroll, BorderLayout.CENTER);

        add(bottomPanel, BorderLayout.SOUTH);

        // Button actions
        addButton.addActionListener(e -> addURL());
        removeButton.addActionListener(e -> removeSelectedURLs());
        startButton.addActionListener(e -> startDownloads());

        setVisible(true);
    }

    private void addURL() {
        String url = urlField.getText().trim();
        if (!url.isEmpty()) {
            urlListModel.addElement(url);
            urlField.setText("");
        }
    }

    private void removeSelectedURLs() {
        java.util.List<String> selected = urlList.getSelectedValuesList();
        for (String url : selected) {
            urlListModel.removeElement(url);
        }
    }

    private void startDownloads() {
        if (urlListModel.isEmpty()) {
            JOptionPane.showMessageDialog(this, "No URLs to download!");
            return;
        }

        executor = Executors.newFixedThreadPool(THREAD_POOL_SIZE);
        progressPanel.removeAll();
        revalidate();

        for (int i = 0; i < urlListModel.size(); i++) {
            String url = urlListModel.get(i);
            JProgressBar progressBar = new JProgressBar(0, 100);
            progressBar.setStringPainted(true);
            progressPanel.add(new JLabel(url));
            progressPanel.add(progressBar);

            executor.submit(() -> downloadFile(url, progressBar));
        }

        executor.shutdown();
    }

    private void downloadFile(String fileURL, JProgressBar progressBar) {
        try {
            URL url = new URL(fileURL);
            String fileName = new File(url.getPath()).getName();
            if (fileName.isEmpty()) {
                fileName = "download_" + System.currentTimeMillis();
            }

            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            int fileSize = connection.getContentLength();

            try (InputStream in = connection.getInputStream();
                 FileOutputStream out = new FileOutputStream(fileName)) {

                byte[] buffer = new byte[4096];
                int bytesRead;
                int totalRead = 0;
                while ((bytesRead = in.read(buffer)) != -1) {
                    out.write(buffer, 0, bytesRead);
                    totalRead += bytesRead;
                    int progress = fileSize > 0 ? (totalRead * 100) / fileSize : 0;
                    SwingUtilities.invokeLater(() -> progressBar.setValue(progress));
                }

                SwingUtilities.invokeLater(() -> progressBar.setString("Downloaded"));
            }
        } catch (IOException e) {
            SwingUtilities.invokeLater(() -> progressBar.setString("Failed: " + e.getMessage()));
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new DownloaderGUI());
    }
}