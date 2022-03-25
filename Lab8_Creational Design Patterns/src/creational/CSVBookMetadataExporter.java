package creational;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Iterator;
import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVPrinter;

public class CSVBookMetadataExporter extends BookMetadataExporter {
    public CSVBookMetadataExporter() {
    }

    public void export(PrintStream stream) throws IOException {
        ArrayList<Book> bookList = super.getBookList();
        CSVBookMetadataFormatter csvFormatter = new CSVBookMetadataFormatter();
        Iterator var4 = bookList.iterator();

        while(var4.hasNext()) {
            Book book = (Book)var4.next();
            csvFormatter.append(book);
        }

        String[] text = csvFormatter.getMetadataString().split(" \n ");

        try {
            CSVPrinter printer = new CSVPrinter(new FileWriter("csvOutput.csv"), CSVFormat.DEFAULT);

            try {
                String[] var6 = text;
                int var7 = text.length;

                for(int var8 = 0; var8 < var7; ++var8) {
                    String s = var6[var8];
                    printer.printRecord(s.split(","));
                }
            } catch (Throwable var11) {
                try {
                    printer.close();
                } catch (Throwable var10) {
                    var11.addSuppressed(var10);
                }

                throw var11;
            }

            printer.close();
        } catch (IOException var12) {
            var12.printStackTrace();
        }

    }
}