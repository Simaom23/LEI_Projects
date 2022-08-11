package projetopoo;

/**
 *
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
import java.util.ArrayList;
import java.util.Comparator;
import java.io.*; 

/**
 * Define os diferentes Investigadores do CISUC.
 * @author Simão Monteiro Nº2019215412
 * @version 1.0
 */
public class Investigador implements Serializable{
    
    private String nome;
    private String email;
    private String grupo;
    private ArrayList<Publicacao> pub;
    private int tipo;

    /**
     * Construtor da classe Investigador.
     * @param nome Nome do Investigador.
     * @param email Email do Investigador
     * @param grupo Grupo do investigador.
     */
    public Investigador(String nome, String email, String grupo) {
        this.nome = nome;
        this.email = email;
        this.grupo = grupo;
        this.pub = new ArrayList<>();
        this.tipo = tipoInvest();
    }

    /**
     *
     * @return Nome do investigador.
     */
    public String getNome() {
        return nome;
    }

    /**
     *
     * @return Email do Investigador.
     */
    public String getEmail() {
        return email;
    }

    /**
     *
     * @return Grupo do investigador.
     */
    public String getGrupo() {
        return grupo;
    }

    /**
     *
     * @return Lista de Publicações do Investigador.
     */
    public ArrayList<Publicacao> getPub() {
        return pub;
    }
    
    /**
     * 
     * @return Tipo do investigador (Efetivo - 1, Estudante - 2, Default - 0).
     */
    
    public int getTipo(){
        return tipo;
    }
    
    /**
     * Dependendo do tipo de investigador devolve o seu tipo (Efetivo - 1, Estudante - 2, Default - 0).
     * @return Tipo de Investigador.
     */
    public int tipoInvest(){
        return 0;
    }
    
    /**
     * Comparator para ordenar os investigadores por tipo.
     */
    public static Comparator<Investigador> investOrganiza = new Comparator<Investigador>() {
        @Override
        public int compare(Investigador i1, Investigador i2) {
            return (int)(i1.getTipo() - i2.getTipo());
        }
    };

    /**
     *
     * @return String para impirmir a informação dos investigadores.
     */
    @Override
    public String toString() {
        return "Investigador -> nome=" + nome + ", email=" + email + ", grupo=" + grupo ;
    }
}
