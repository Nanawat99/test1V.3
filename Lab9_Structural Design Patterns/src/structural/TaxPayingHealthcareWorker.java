package structural;

public class TaxPayingHealthcareWorker extends HealthcareWorkerDecorator {

    public TaxPayingHealthcareWorker(HealthcareWorker worker) {
        super(worker);
        System.out.printf("Decorate " + worker.getName() + " with TaxPaying\n");
    }

    public double getPrice() {
        return super.getPrice() * 1.1D;
    }
}
