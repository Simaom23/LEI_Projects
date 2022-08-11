package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nº2019215412
 */
public class Regular extends Cliente {

    public Regular(String nome, String email) {
        super(nome, email);
    }

    @Override
    public double getDesconto() {
        return 1;
    }
}
