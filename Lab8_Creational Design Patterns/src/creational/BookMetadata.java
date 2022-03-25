package creational;

public enum BookMetadata {
    ISBN("ISBN"),
    TITLE("Title"),
    PUBLISHER("Publisher"),
    AUTHORS("Authors");

    public final String value;

    private BookMetadata(String value) {
        this.value = value;
    }

    public static String getValue(BookMetadata messages) {
        return messages.value;
    }
}
