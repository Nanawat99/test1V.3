package creational;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import javax.xml.stream.XMLStreamException;

public class Main {
    public static void main(String[] args) throws XMLStreamException, IOException, ParserConfigurationException {
        BookMetadataExporter exporter = new JSONBookMetadataExporter();
        exporter.add(Test.sailboatBook);
        exporter.add(Test.GoFBook);
        exporter.export(System.out);
        BookMetadataExporter exporterXML = new XMLBookMetadataExporter();
        exporterXML.add(Test.sailboatBook);
        exporterXML.add(Test.GoFBook);
        exporterXML.export(System.out);
        BookMetadataExporter exporterCSV = new CSVBookMetadataExporter();
        exporterCSV.add(Test.sailboatBook);
        exporterCSV.add(Test.GoFBook);
        exporterCSV.export(System.out);
    }
}
