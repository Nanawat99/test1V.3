package structural;

public abstract class HealthcareWorkerDecorator extends HealthcareWorker {
    private HealthcareWorker worker = null;

    public HealthcareWorkerDecorator(HealthcareWorker wrapWorker) {
        super(wrapWorker.getName(), wrapWorker.getPrice());
        this.worker = wrapWorker;
    }

    public void service() {
        this.worker.service();
    }

    public double getPrice() {
        return this.worker.getPrice();
    }
}