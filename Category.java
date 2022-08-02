public class Category {
    int type;
    int wClass;
    int damageLow;
    int damageHigh;
    int concealmentLow;
    int concealmentHigh;
    int rofLow;
    int rofHigh;
    int accuracyLow;
    int accuracyHigh;
    int stabilityLow;
    int stabilityHigh;
    float ammoLowLow;
    float ammoLowHigh;
    float ammoHighLow;
    float ammoHighHigh;
    int magSizeLow;
    int magSizeHigh;
    int ammoTotalLow;
    int ammoTotalHigh;

    public Category() {

    }

    public Category(int type, int wClass, int damage, int concealment, int rof, int accuracy, int stability, float ammoLow, float ammoHigh, int magSize, int ammoTotal) {
        this.type = type;
        this.wClass = wClass;
        this.damageLow = damage;
        this.damageHigh = damage;
        this.concealmentLow = concealment;
        this.concealmentHigh = concealment;
        this.rofLow = rof;
        this.rofHigh = rof;
        this.accuracyLow = accuracy;
        this.accuracyHigh = accuracy;
        this.stabilityLow = stability;
        this.stabilityHigh = stability;
        this.ammoLowLow = ammoLow;
        this.ammoLowHigh = ammoLow;
        this.ammoHighLow = ammoHigh;
        this.ammoHighHigh = ammoHigh;
        this.magSizeLow = magSize;
        this.magSizeHigh = magSize;
        this.ammoTotalLow = ammoTotal;
        this.ammoTotalHigh = ammoTotal;
    }

    public void updateStats(Weapon w) {
        this.damageLow = Math.min(w.damage, this.damageLow);
        this.damageHigh = Math.max(w.damage, this.damageHigh);
        this.concealmentLow = Math.min(w.concealment, this.concealmentLow);
        this.concealmentHigh = Math.max(w.concealment, this.concealmentHigh);
        this.rofLow = Math.min(w.rof, this.rofLow);
        this.rofHigh = Math.max(w.rof, this.rofHigh);
        this.accuracyLow = Math.min(w.accuracy, this.accuracyLow);
        this.accuracyHigh = Math.max(w.accuracy, this.accuracyHigh);
        this.stabilityLow = Math.min(w.stability, this.stabilityLow);
        this.stabilityHigh = Math.max(w.stability, this.stabilityHigh);
        this.ammoLowLow = Math.min(w.ammoLow, this.ammoLowLow);
        this.ammoLowHigh = Math.max(w.ammoLow, this.ammoLowHigh);
        this.ammoHighLow = Math.min(w.ammoHigh, this.ammoHighLow);
        this.ammoHighHigh = Math.max(w.ammoHigh, this.ammoHighHigh);
        this.magSizeLow = Math.min(w.magSize, this.magSizeLow);
        this.magSizeHigh = Math.max(w.magSize, this.magSizeHigh);
        this.ammoTotalLow = Math.min(w.ammoTotal, this.ammoTotalLow);
        this.ammoTotalHigh = Math.max(w.ammoTotal, this.ammoTotalHigh);
    }

    public int getType() {
        return type;
    }

    public int getWClass() {
        return wClass;
    }

    public int getDamageLow() {
        return damageLow;
    }

    public void setDamageLow(int damageLow) {
        this.damageLow = damageLow;
    }

    public int getDamageHigh() {
        return damageHigh;
    }

    public void setDamageHigh(int damageHigh) {
        this.damageHigh = damageHigh;
    }

    public int getConcealmentLow() {
        return concealmentLow;
    }

    public void setConcealmentLow(int concealmentLow) {
        this.concealmentLow = concealmentLow;
    }

    public int getConcealmentHigh() {
        return concealmentHigh;
    }

    public void setConcealmentHigh(int concealmentHigh) {
        this.concealmentHigh = concealmentHigh;
    }

    public int getRofLow() {
        return rofLow;
    }

    public void setRofLow(int rofLow) {
        this.rofLow = rofLow;
    }

    public int getRofHigh() {
        return rofHigh;
    }

    public void setRofHigh(int rofHigh) {
        this.rofHigh = rofHigh;
    }

    public int getAccuracyLow() {
        return accuracyLow;
    }

    public void setAccuracyLow(int accuracyLow) {
        this.accuracyLow = accuracyLow;
    }

    public int getAccuracyHigh() {
        return accuracyHigh;
    }

    public void setAccuracyHigh(int accuracyHigh) {
        this.accuracyHigh = accuracyHigh;
    }

    public int getStabilityLow() {
        return stabilityLow;
    }

    public void setStabilityLow(int stabilityLow) {
        this.stabilityLow = stabilityLow;
    }

    public int getStabilityHigh() {
        return stabilityHigh;
    }

    public void setStabilityHigh(int stabilityHigh) {
        this.stabilityHigh = stabilityHigh;
    }

    public float getAmmoLowLow() {
        return ammoLowLow;
    }

    public void setAmmoLowLow(float ammoLowLow) {
        this.ammoLowLow = ammoLowLow;
    }

    public float getAmmoLowHigh() {
        return ammoLowHigh;
    }

    public void setAmmoLowHigh(float ammoLowHigh) {
        this.ammoLowHigh = ammoLowHigh;
    }

    public float getAmmoHighLow() {
        return ammoHighLow;
    }

    public void setAmmoHighLow(float ammoHighLow) {
        this.ammoHighLow = ammoHighLow;
    }

    public float getAmmoHighHigh() {
        return ammoHighHigh;
    }

    public void setAmmoHighHigh(float ammoHighHigh) {
        this.ammoHighHigh = ammoHighHigh;
    }

    public int getMagSizeLow() {
        return magSizeLow;
    }

    public void setMagSizeLow(int magSizeLow) {
        this.magSizeLow = magSizeLow;
    }

    public int getMagSizeHigh() {
        return magSizeHigh;
    }

    public void setMagSizeHigh(int magSizeHigh) {
        this.magSizeHigh = magSizeHigh;
    }

    public int getAmmoTotalLow() {
        return ammoTotalLow;
    }

    public void setAmmoTotalLow(int ammoTotalLow) {
        this.ammoTotalLow = ammoTotalLow;
    }

    public int getAmmoTotalHigh() {
        return ammoTotalHigh;
    }

    public void setAmmoTotalHigh(int ammoTotalHigh) {
        this.ammoTotalHigh = ammoTotalHigh;
    }
}