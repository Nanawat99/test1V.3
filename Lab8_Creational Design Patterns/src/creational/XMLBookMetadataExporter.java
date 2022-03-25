package creational;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.io.Writer;
import java.util.ArrayList;
import java.util.Iterator;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLOutputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamWriter;

public class XMLBookMetadataExporter extends BookMetadataExporter {
    public XMLBookMetadataExporter() {
    }

    public void export(PrintStream stream) throws IOException, XMLStreamException, ParserConfigurationException {
        ArrayList<Book> bookList = super.getBookList();
        XMLBookMetadataFormatter xmlFormatter = new XMLBookMetadataFormatter();
        Iterator var4 = bookList.iterator();

        while(var4.hasNext()) {
            Book book = (Book)var4.next();
            xmlFormatter.append(book);
        }

        String filePath = "xmlOutput.xml";
        Writer fileWriter = new FileWriter(filePath);
        XMLOutputFactory xmlOutputFactory = XMLOutputFactory.newInstance();
        XMLStreamWriter xmlStreamWriter = xmlOutputFactory.createXMLStreamWriter(fileWriter);
        xmlStreamWriter.writeCData(xmlFormatter.getMetadataString());
        xmlStreamWriter.flush();
        xmlStreamWriter.close();
    }
}