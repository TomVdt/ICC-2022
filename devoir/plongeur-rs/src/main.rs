#[derive(Clone)]
struct Conditions {
    profondeur: f64,
    vitesse: f64,
    temps: f64
}

struct Diver<'a> {
    nom: &'a str,
    masse: f64,
    volume: f64,
    acceleration: f64,
    condition: Conditions
}

struct Status {
    vmax: bool,
    profond: bool,
    ballon: bool
}

const VOLUME_BALLON: f64 = 0.0375;
const PROFONDEUR_DESIREE: f64 = -40.0;
const PROFONDEUR_BALLON: f64 = -43.0;
const SEUIL_VMAX: f64 = 1e-5;

fn display(d: &Diver) {
    println!("{}, {:.5}, {:.5}, {:.5}", d.condition.temps, d.condition.profondeur, d.condition.vitesse, d.acceleration);
}

fn message(d: &Diver, mess: &str, valeur: f64, unite: &str) {
    println!("## (t = {}) {} {} ({:.5} {})", d.condition.temps, d.nom, mess, valeur, unite);
}

fn evolve(d: &mut Diver, cond: &Conditions) {
    d.condition.temps += 1.0;

    let g: f64 = 9.81;
    let t = cond.temps - d.condition.temps;
    let mu = 1.0 - 1000.0 * (d.volume / d.masse);
    let alpha = t.exp();
    let k = cond.vitesse - g * mu;

    d.condition.vitesse = (alpha * k) + (g * mu);
    d.acceleration = -(alpha * k);
    d.condition.profondeur = cond.profondeur + (k * (alpha - 1.0)) + (t * g * mu);
}

fn update_status(d: &mut Diver, cond: &mut Conditions, status: &mut Status) {
    if d.acceleration < SEUIL_VMAX && !status.vmax {
        status.vmax = true;
        message(d, "a atteind sa vitesse maximale", d.acceleration, "ms-2");
    }
    if d.condition.profondeur < PROFONDEUR_DESIREE && !status.profond {
        status.profond = true;
        message(d, "a atteind la profondeur désirée", d.condition.profondeur, "m");
    }
    if d.condition.profondeur < PROFONDEUR_BALLON && !status.ballon {
        status.ballon = true;
        d.volume += VOLUME_BALLON;
        cond.vitesse = 0.0;
        cond.profondeur = d.condition.profondeur;
        cond.temps = d.condition.temps;
        message(d, "s'arrête et gonfle son ballon", d.condition.profondeur, "m");
    }
}

fn dive(mut d: Diver) {
    if d.condition.profondeur > 0.0 || d.masse <= 0.0 || d.volume <= 0.0 {
        eprintln!("ptdr t con");
        return;
    }

    let mut conditions_init: Conditions = d.condition.clone();
    let mut status: Status = Status { vmax: false, profond: false, ballon: false };

    while d.condition.profondeur < 0.0 {
        display(&d);
        evolve(&mut d, &conditions_init);
        update_status(&mut d, &mut conditions_init, &mut status);
    }

    message(&d, "est de retour à la surface", d.condition.profondeur, "m");
}

fn main() {
    let diver: Diver = Diver {
        nom: "Jacques",
        masse: 90.0,
        volume: 0.075,
        acceleration: 0.0,
        condition: Conditions { profondeur: -1.2, vitesse: 0.8, temps: 0.0 }
    };

    dive(diver);
}
