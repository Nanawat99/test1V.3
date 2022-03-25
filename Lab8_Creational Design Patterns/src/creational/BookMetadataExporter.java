package creational;

import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLStreamException;

public abstract class BookMetadataExporter extends BookCollection {
    private final ArrayList<Book> bookList = new ArrayList();

    public BookMetadataExporter() {
    }

    public abstract void export(PrintStream stream) throws IOException, XMLStreamException, ParserConfigurationException;

    public ArrayList<Book> getBookList() {
        return this.bookList;
    }

    public void add(Book book) {
        this.bookList.add(book);
    }
}
