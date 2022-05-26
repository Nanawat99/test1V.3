package behavioral;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.concurrent.Flow.Publisher;
import java.util.concurrent.Flow.Subscriber;

public class NewsPublisher implements Publisher<News> {
    private final List<NewsReader> NewsReaders = new ArrayList();

    public NewsPublisher() {
    }

    public void subscribe(NewsReader NewsReader) {
        this.NewsReaders.add(NewsReader);
    }

    public void removeSubscriber(NewsReader NewsReader) {
        this.NewsReaders.remove(NewsReader);
    }

    void publish(News news) {
        Iterator list = this.NewsReaders.iterator();

        while(list.hasNext()) {
            NewsReader reader = (NewsReader)list.next();
            reader.update(news);
        }

    }

    public void subscribe(Subscriber<? super News> subscriber) {
        throw new UnsupportedOperationException("Not supported yet.");
    }
}
