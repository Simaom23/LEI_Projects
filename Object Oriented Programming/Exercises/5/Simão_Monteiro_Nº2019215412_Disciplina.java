package exercicioavaliacao5;

/**
 *
 * @author Simão Monteiro
 */
import java.util.ArrayList;
import java.io.*;

public class Disciplina implements Serializable {

    private String nomeDisciplina;
    private String sigla;
    private int ects;
    private ArrayList<Aluno> inscritos;

    public Disciplina(String nomeDisciplina, String sigla, int ects, ArrayList<Aluno> inscritos) {
        this.nomeDisciplina = nomeDisciplina;
        this.sigla = sigla;
        this.ects = ects;
        this.inscritos = inscritos;
    }

    public String getNomeDisciplina() {
        return nomeDisciplina;
    }

    public int getEcts() {
        return ects;
    }

    public ArrayList<Aluno> getInscritos() {
        return inscritos;
    }

    public String getSigla() {
        return sigla;
    }

    public void newInscrito(Aluno newAluno) {
        if(inscritos.indexOf(newAluno) == -1){
            inscritos.add(newAluno);
        }
        else{
            System.out.printf("\nO aluno com o número %d já se encontra escrito.\n\n", newAluno.getNumAluno());
        }
    }
    
    public void delInscrito(Aluno delAluno){
        int del = inscritos.indexOf(delAluno);
        if(del != -1){
            inscritos.remove(del);
        }
        else{
            System.out.printf("\nO aluno com o número %d já não se encontra escrito.\n\n", delAluno.getNumAluno());
        }
    }

    @Override
    public String toString() {
        String toPrint = nomeDisciplina + " - " + sigla + " - " + ects+ " ECTS" + "\n";
        for (Aluno listarInscritos : inscritos) {
            toPrint += listarInscritos.toString();
        }
        return toPrint;
    }
}
