import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.ThreadLocalRandom;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class WeaponStatRandomizer {
    public static void main(String[] args) {
        final File f = new File(WeaponStatRandomizer.class.getProtectionDomain().getCodeSource().getLocation().getPath());
        String path = f.getAbsolutePath().replaceAll("%20", " ");
        int convenientCounter = path.lastIndexOf("\\");
        String[] a = {path.substring(0, convenientCounter), path.substring(convenientCounter + 1)};
        path = a[0];
        Scanner input = new Scanner(System.in);
        boolean check = false;
        String keyInput;
        System.out.println("This program serves as the selector for the Weapon Stat Randomizer for PAYDAY 2. " +
                "It will randomize damage, fire rate and ammo pickup of all weapons within the limits set " +
                "in weaponList.txt");
        while (!check) {
            System.out.println("Do you want to randomize? (This will delete your previous randomization.)");
            keyInput = input.nextLine();
            if (keyInput.equalsIgnoreCase("Y")) {
                check = true;
            } else {
                System.out.println("Invalid input.");
            }
        }
        //creation and nesting of necessary lists
        LinkedList<Weapon> assaultRifles = new LinkedList<>();
        LinkedList<Weapon> shotguns = new LinkedList<>();
        LinkedList<Weapon> lmgs = new LinkedList<>();
        LinkedList<Weapon> snipers = new LinkedList<>();
        LinkedList<Weapon> x_pistols = new LinkedList<>();
        LinkedList<Weapon> x_smgs = new LinkedList<>();
        LinkedList<Weapon> x_shotguns = new LinkedList<>();
        LinkedList<Weapon> specialP = new LinkedList<>();
        LinkedList<Weapon> pistols = new LinkedList<>();
        LinkedList<Weapon> smgs = new LinkedList<>();
        LinkedList<Weapon> specialS = new LinkedList<>();
        LinkedList<Weapon> shotgunsS = new LinkedList<>();
        LinkedList<Weapon> snipersS = new LinkedList<>();
        LinkedList<LinkedList<Weapon>> primaries = new LinkedList<>();
        LinkedList<LinkedList<Weapon>> secondaries = new LinkedList<>();
        primaries.add(assaultRifles);
        primaries.add(shotguns);
        primaries.add(lmgs);
        primaries.add(snipers);
        primaries.add(x_pistols);
        primaries.add(x_smgs);
        primaries.add(x_shotguns);
        primaries.add(specialP);
        secondaries.add(pistols);
        secondaries.add(smgs);
        secondaries.add(specialS);
        secondaries.add(shotgunsS);
        secondaries.add(snipersS);
        List<String> weaponList = null;
        LinkedList<LinkedList<LinkedList<Weapon>>> allWeapons = new LinkedList<>();
        allWeapons.add(primaries);
        allWeapons.add(secondaries);
        //open .csv file
        try (Stream<String> lines = Files.lines(Paths.get(path + "\\originalStats.csv"))) {
            weaponList = lines.collect(Collectors.toList());
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("An error occurred (trying to read originalStats.csv).");
            System.exit(1);
        }
        //read .csv file per line and data to corresponding lists
        for (String temp : weaponList) {
            String[] res = temp.split(",", 0);
            Weapon p = new Weapon(res[0], Integer.parseInt(res[1]), Integer.parseInt(res[2]), res[3], Integer.parseInt(res[4]), Integer.parseInt(res[5]), Integer.parseInt(res[6]), Integer.parseInt(res[7]), Integer.parseInt(res[8]), Float.parseFloat(res[9]), Float.parseFloat(res[10]), Integer.parseInt(res[11]), Integer.parseInt(res[12]));
            if (p.type <= 8) {
                primaries.get(p.type - 1).add(p);
            } else {
                secondaries.get(p.type - 9).add(p);
            }
        }
        //create .lua file (delete if it already exists)
        try {
            File myObj = new File(path + "\\WeaponStats.lua");
            if (myObj.createNewFile()) {
                System.out.println("File created: " + myObj.getName());
            } else {
                File weaponStats = new File(path + "\\WeaponStats.lua");
                weaponStats.delete();
                myObj.createNewFile();
                System.out.println("WeaponStats.lua has been deleted and replaced.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred (creating or deleting WeaponStats.lua, check permissions).");
            e.printStackTrace();
            System.exit(1);
        }
        //create hashmap for categories and update the categories with data from the lists
        HashMap<String, Category> categories = new HashMap<String, Category>();
        for (LinkedList<LinkedList<Weapon>> allWeapon : allWeapons) {
            for (LinkedList<Weapon> weapons : allWeapon) {
                for (Weapon weaponTemp : weapons) {
                    Category c = categories.get(weaponTemp.getType() + ", " + weaponTemp.getWClass());
                    if (c == null) {
                        categories.put(weaponTemp.getType() + ", " + weaponTemp.getWClass(), new Category(weaponTemp.getType(), weaponTemp.getWClass(), weaponTemp.getDamage(), weaponTemp.getConcealment(), weaponTemp.getRof(), weaponTemp.getAccuracy(), weaponTemp.getStability(), weaponTemp.getAmmoLow(), weaponTemp.getAmmoHigh(), weaponTemp.getMagSize(), weaponTemp.getAmmoTotal()));
                    } else {
                        c.updateStats(weaponTemp);
                    }
                }
            }
        }
        //write .lua file
        try {
            FileWriter fileWriter = new FileWriter(path + "\\WeaponStats.lua");
            PrintWriter printWriter = new PrintWriter(fileWriter);
            printWriter.println("local old_init = WeaponTweakData.init\n\nfunction WeaponTweakData:init(tweak_data)\n    old_init(self, tweak_data)\n\t");
            //seed based randomization
            Random random = new Random();
            long seed = ThreadLocalRandom.current().nextLong();
            //replace "seed" with given seed+L (i.e. 123456789L) to replicate values
            random.setSeed(seed);
            for (LinkedList<LinkedList<Weapon>> allWeapon2 : allWeapons) {
                for (LinkedList<Weapon> weapons : allWeapon2) {
                    for (Weapon weaponTemp : weapons) {
                        String name = weaponTemp.getInternalName();
                        Category c = categories.get(weaponTemp.getType() + ", " + weaponTemp.getWClass());
                        int damage = random.nextInt(c.damageHigh * 4 / 3 - c.damageLow * 3 / 4) + c.damageLow * 3 / 4;
                        float coefficient1 = c.damageHigh / (float) damage;
                        coefficient1 = random.nextFloat(coefficient1 * 4 / 3 - coefficient1 * 3 / 4) + coefficient1 * 3 / 4;
                        int concealment = (int) (random.nextFloat(c.concealmentHigh * coefficient1 - c.concealmentLow * coefficient1 + 0.01f) + c.concealmentLow * coefficient1);
                        concealment = concealment > 0 ? concealment : 1;
                        float coefficient2 = c.concealmentHigh / (float) concealment;
                        float coefficient = (coefficient1 + coefficient2) / 2;
                        float rof = 60 / (random.nextFloat(c.rofHigh * coefficient - c.rofLow * coefficient + 0.01f) + c.rofLow * coefficient);
                        int accuracy = (int) (random.nextFloat(c.accuracyHigh * coefficient - c.accuracyLow * coefficient + 0.01f) + c.accuracyLow * coefficient);
                        int stability = (int) (random.nextFloat(c.stabilityHigh * coefficient - c.stabilityLow * coefficient + 0.01f) + c.stabilityLow * coefficient);
                        float ammoLow = random.nextFloat(c.ammoLowHigh * coefficient - c.ammoLowLow * coefficient + 0.01f) + c.ammoLowLow * coefficient;
                        float ammoHigh = random.nextFloat(c.ammoHighHigh * coefficient - c.ammoHighLow * coefficient + 0.01f) + c.ammoHighLow * coefficient;
                        int magSize = (int) (random.nextFloat(c.magSizeHigh * coefficient - c.magSizeLow * coefficient + 0.01f) + c.magSizeLow * coefficient);
                        int ammoTotal = (int) (random.nextFloat(c.ammoTotalHigh * coefficient - c.ammoTotalLow * coefficient + 0.01f) + c.ammoTotalLow * coefficient);
                        //damage reduction for weapons, where PAYDAY 2 multiplies the base damage itself (i.e. snipers)
                        damage = weaponTemp.type == 4 && weaponTemp.wClass == 2 ? Math.round(damage/2f) : damage;
                        damage = weaponTemp.type == 4 && weaponTemp.wClass == 3 ? Math.round(damage/4f) : damage;
                        damage = weaponTemp.type == 4 && weaponTemp.wClass == 4 ? Math.round(damage/35f) : damage;
                        damage = weaponTemp.type == 4 && weaponTemp.wClass == 2 ? Math.round(damage/2f) : damage;
                        damage = weaponTemp.type == 9 && weaponTemp.wClass == 6 ? Math.round(damage/2f) : damage;
                        damage = weaponTemp.type == 12 && weaponTemp.wClass == 9 ? Math.round(damage/2f) : damage;
                        damage = weaponTemp.type == 13 && weaponTemp.wClass == 1 ? Math.round(damage/2f) : damage;
                        printWriter.println("self." + name + ".stats.damage = " + damage);
                        printWriter.println("self." + name + ".stats.concealment = " + concealment);
                        printWriter.printf("self." + name + ".fire_mode_data = {fire_rate = " + (String.format(Locale.US, "%.2f", rof)) + "}\n");
                        printWriter.printf("self." + name + ".auto = {fire_rate = " + (String.format(Locale.US, "%.2f", rof)) + "}\n");
                        printWriter.printf("self." + name + ".stats.spread = " + (Math.round(accuracy / 4f) + 1) + "\n");
                        printWriter.printf("self." + name + ".stats.recoil = " + (Math.round(stability / 4f) + 1) + "\n");
                        printWriter.printf("self." + name + ".AMMO_PICKUP = {" + String.format(Locale.US, "%.2f", ammoLow) + ", " + String.format(Locale.US, "%.2f", ammoHigh) + "}\n");
                        printWriter.println("self." + name + ".CLIP_AMMO_MAX = " + magSize);
                        printWriter.println("self." + name + ".AMMO_MAX = " + ammoTotal);
                    }
                }
            }
            printWriter.println("\nend");
            printWriter.print("--Seed: " + seed);
            printWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred (PrintWriter).");
            e.printStackTrace();
            System.exit(1);
        }
    }
}
