package structural;

public class Main {
    public Main() {
    }

    public static void main(String[] args) {
        HealthcareWorkerTeam teamMedicalDragon = new HealthcareWorkerTeam();
        Surgeon ryutarou = new Surgeon("Ryutarou Asada", 0.00D);
        Nurse miki = new Nurse("Miki Satohara", 1000.00D);
        Cardiologist keisuke = new Cardiologist("Keisuke Fujiyoshi", 1000.00D);
        Anesthesiologist monji = new Anesthesiologist("Monji Arase", 10000.00D);
        teamMedicalDragon.addMember(ryutarou);
        teamMedicalDragon.addMember(miki);
        teamMedicalDragon.addMember(keisuke);
        teamMedicalDragon.addMember(monji);
        System.out.println("================================");
        monji.service();
        System.out.println("Monji's price is " + monji.getPrice());
        teamMedicalDragon.service();
        System.out.println("Before Monji leaves, the total price of the Team Medical Dragon is " + teamMedicalDragon.getPrice());
        teamMedicalDragon.removeMember(monji);
        System.out.println("After Monji leaves, The total price of the Team Medical Dragon is " + teamMedicalDragon.getPrice());
        System.out.println("================================");
        HealthcareWorkerTeam theGoodDoctor = new HealthcareWorkerTeam();
        Surgeon freddie = new Surgeon("Freddie Highmore", 550.00D);
        Surgeon nicholas = new Surgeon("Nicholas Gonzalez", 2200.00D);
        HealthcareWorkerDecorator timeNicholas = new TimeLoggingHealthcareWorker(nicholas);
        HealthcareWorkerDecorator taxNicholas = new TaxPayingHealthcareWorker(timeNicholas);
        Surgeon antonia = new Surgeon("Antonia Thomas", 500.00D);
        HealthcareWorkerDecorator timeAnotonia = new TimeLoggingHealthcareWorker(antonia);
        Surgeon chuku = new Surgeon("Chuku Modu", 500.00D);
        theGoodDoctor.addMember(freddie);
        theGoodDoctor.addMember(taxNicholas);
        theGoodDoctor.addMember(timeAnotonia);
        theGoodDoctor.addMember(chuku);
        System.out.println("================================");
        theGoodDoctor.service();
        System.out.println("The total price of the Good Doctor Team is " + theGoodDoctor.getPrice());
        System.out.println("================================");
        HealthcareWorkerTeam KMITL_Doctor = new HealthcareWorkerTeam();
        Surgeon Pasin = new Surgeon("Pasin C", 1500.00D);
        Surgeon Paritat = new Surgeon("Paritat t", 3300.00D);
        KMITL_Doctor.addMember(Pasin);
        KMITL_Doctor.addMember(Paritat);
        System.out.println("================================");
        theGoodDoctor.service();
        System.out.println("The total price of KMITL Doctor Team is " + KMITL_Doctor.getPrice());
        System.out.println("================================");
        HealthcareWorkerTeam healthcareSeries = new HealthcareWorkerTeam();
        healthcareSeries.addMember(teamMedicalDragon);
        healthcareSeries.addMember(theGoodDoctor);
        healthcareSeries.addMember(KMITL_Doctor);
        System.out.println("The total price of the healthcare series is " + healthcareSeries.getPrice());
    }
}