package structural;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class TimeLoggingHealthcareWorker extends HealthcareWorkerDecorator {
    public TimeLoggingHealthcareWorker(HealthcareWorker worker) {
        super(worker);
        System.out.printf("Decorate " + worker.getName() + " with TimeLogging\n");
    }

    public void service() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");
        LocalDateTime now = LocalDateTime.now();
        System.out.printf(formatter.format(now) + " : ");
        super.service();
    }
}
