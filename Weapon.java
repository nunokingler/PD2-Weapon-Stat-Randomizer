public class Weapon {
    String internalName;
    int type;
    int wClass;
    String ingameName;
    int damage;
    int concealment;
    int rof;
    int accuracy;
    int stability;
    float ammoLow;
    float ammoHigh;
    int magSize;
    int ammoTotal;

    public Weapon(String internalName, int type, int wClass, String ingameName, int damage, int concealment, int rof, int accuracy, int stability, float ammoLow, float ammoHigh, int magSize, int ammoTotal) {
        this.internalName = internalName;
        this.type = type;
        this.wClass = wClass;
        this.ingameName = ingameName;
        this.damage = damage;
        this.concealment = concealment;
        this.rof = rof;
        this.accuracy = accuracy;
        this.stability = stability;
        this.ammoLow = ammoLow;
        this.ammoHigh = ammoHigh;
        this.magSize = magSize;
        this.ammoTotal = ammoTotal;
    }

    public String getInternalName() {
        return internalName;
    }

    public int getType() {
        return type;
    }

    public int getWClass() {
        return wClass;
    }

    public String getIngameName() {
        return ingameName;
    }

    public int getDamage() {
        return damage;
    }

    public int getConcealment() {
        return concealment;
    }
    public int getRof() {
        return rof;
    }

    public int getAccuracy() {
        return accuracy;
    }

    public int getStability() {
        return stability;
    }


    public float getAmmoLow() {
        return ammoLow;
    }

    public float getAmmoHigh() {
        return ammoHigh;
    }

    public int getMagSize() {
        return magSize;
    }

    public int getAmmoTotal() {
        return ammoTotal;
    }
}
