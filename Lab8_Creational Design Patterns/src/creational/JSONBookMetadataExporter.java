package creational;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Iterator;

public class JSONBookMetadataExporter extends BookMetadataExporter {
    public JSONBookMetadataExporter() {
    }

    public void export(PrintStream stream) throws IOException {
        ArrayList<Book> bookList = super.getBookList();
        JSONBookMetadataFormatter jsonFormatter = new JSONBookMetadataFormatter();
        FileWriter file = null;
        Iterator var5 = bookList.iterator();

        while(var5.hasNext()) {
            Book book = (Book)var5.next();
            jsonFormatter.append(book);
        }

        try {
            file = new FileWriter("jsonOutput.txt");
            jsonFormatter.getJsonArray().writeJSONString(file);
        } catch (IOException var10) {
            var10.printStackTrace();
        } finally {
            file.flush();
            file.close();
        }

    }
}
