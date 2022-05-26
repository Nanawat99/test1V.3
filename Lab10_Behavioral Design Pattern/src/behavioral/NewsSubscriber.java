package behavioral;

import java.util.concurrent.Flow.Subscriber;

public interface NewsSubscriber {
    void update(News news);
}
