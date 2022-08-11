package exercicioavaliacao4;

/**
 * @author Simão Monteiro Nº2019215412
 */
public class Premium extends Cliente {

    public Premium(String nome, String email) {
        super(nome, email);
    }

    @Override
    public double getDesconto() {
        return 0.90;
    }
}
