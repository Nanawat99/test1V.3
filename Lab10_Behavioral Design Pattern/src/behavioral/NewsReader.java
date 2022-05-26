package behavioral;

public class NewsReader implements NewsSubscriber{
    private final String new_reader_name;

    public NewsReader(String name) {
        this.new_reader_name = name;
    }

    public void update(News news) {
        System.out.println(this.new_reader_name + " got news topic about : " + news.getTopic().toString() + " content : " + news.getContent());
    }
}
