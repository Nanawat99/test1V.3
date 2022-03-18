ackage com.solid.book;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class BookReader implements Reader{

    public static void main(String[] args) {

        BookReader bookreader = new BookReader();
        bookreader.printToScreen();
    }

    @Override
    public void printToScreen() {
        Book book = new Book("Book", List.of("Chapter 1", "Chapter 2", "Chapter 3", "Chapter 4", "Chapter 5"));
        do {
            System.out.println(book.getCurrentPage());
        } while (book.turnToNextPage());
    }
}
