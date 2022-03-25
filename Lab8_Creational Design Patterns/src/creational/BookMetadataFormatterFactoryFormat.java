package creational;


public enum BookMetadataFormatterFactoryFormat {
    CSV("CSV"),
    XML("XML"),
    JSON("JSON");

    public final String value;

    private BookMetadataFormatterFactoryFormat(String value) {
        this.value = value;
    }
}
