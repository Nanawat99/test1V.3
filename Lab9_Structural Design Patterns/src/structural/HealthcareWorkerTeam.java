package structural;

import java.util.ArrayList;
import java.util.Iterator;

public class HealthcareWorkerTeam implements HealthcareServiceable {
    private ArrayList<HealthcareServiceable> members = new ArrayList();

    public HealthcareWorkerTeam() {
    }

    public void addMember(HealthcareServiceable newMember) {
        this.members.add(newMember);
    }

    public void removeMember(HealthcareServiceable removeMember) {
        this.members.remove(removeMember);
    }

    public void service() {
        Iterator x = this.members.iterator();

        while(x.hasNext()) {
            HealthcareServiceable member = (HealthcareServiceable)x.next();
            member.service();
        }

    }

    public double getPrice() {
        double price = 0.00D;

        HealthcareServiceable member;
        for(Iterator x= this.members.iterator(); x.hasNext(); price += member.getPrice()) {
            member = (HealthcareServiceable)x.next();
        }

        return price;
    }
}