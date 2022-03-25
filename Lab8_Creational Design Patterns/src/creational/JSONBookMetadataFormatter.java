package creational;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class JSONBookMetadataFormatter implements BookMetadataFormatter {
    private JSONArray arr;

    public JSONBookMetadataFormatter() {
        this.reset();
    }

    public BookMetadataFormatter reset() {
        this.arr = new JSONArray();
        return this;
    }

    public BookMetadataFormatter append(Book b) {
        JSONObject obj = new JSONObject();
        obj.put("ISBN", b.getISBN());
        obj.put("Title", b.getTitle());
        obj.put("Publisher", b.getPublisher());
        String[] author = b.getAuthors();
        String AllAuthor = "";

        for(int i = 0; i < author.length; ++i) {
            if (i != author.length - 1) {
                AllAuthor = AllAuthor + author[i] + " | ";
            } else {
                AllAuthor = AllAuthor + author[i];
            }
        }

        obj.put("Author", AllAuthor);
        this.arr.add(obj);
        return this;
    }

    public String getMetadataString() {
        return this.arr.toString();
    }

    public JSONArray getJsonArray() {
        return this.arr;
    }
}