package exercicioavaliacao5;

/**
 *
 * @author Simão Monteiro
 */
import java.util.ArrayList;

public class Inscricao {

    private ArrayList<Aluno> listaAlunos;
    private ArrayList<Disciplina> listaDisciplinas;

    public Inscricao() {
        this.listaAlunos = new ArrayList<>();
        this.listaDisciplinas = new ArrayList<>();
    }

    public ArrayList<Aluno> getListaAlunos() {
        return listaAlunos;
    }

    public ArrayList<Disciplina> getListaDisciplinas() {
        return listaDisciplinas;
    }
    
    
    public void addAluno(Aluno newAluno) {
        listaAlunos.add(newAluno);
    }
    
    public Aluno searchAluno(int num){
        int indice = -1;
        Aluno rAluno = null;
        for (Aluno searchAluno : listaAlunos) {
            if (searchAluno.getNumAluno() == num) {
                indice = listaAlunos.indexOf(searchAluno);
                rAluno = listaAlunos.get(indice);
            }
        }
        if (indice == -1) {
            System.out.printf("\nO aluno com o %d não se encontra na base de dados.\n\n", num);
        }
        return rAluno;
    }
    
    public void addDisciplina(Disciplina newDisciplina) {
        listaDisciplinas.add(newDisciplina);
    }

    public void listarDisciplinas() {
        for (Disciplina listar : listaDisciplinas) {
            System.out.println(listar);
        }
    }

    public void addInscricao(int num, String sigla) {
        Aluno newAluno = null;
        int indice = -1; 
        for (Aluno searchAluno : listaAlunos) {
            if (searchAluno.getNumAluno() == num) {
                indice = listaAlunos.indexOf(searchAluno);
                newAluno = listaAlunos.get(indice);
            }
        }
        if (indice != -1) {
            int indiceDis = -1;
            for (Disciplina searchDisciplina : listaDisciplinas) {
                if (searchDisciplina.getSigla().toLowerCase().equals(sigla.toLowerCase())) {
                    indiceDis = listaDisciplinas.indexOf(searchDisciplina);
                    searchDisciplina.newInscrito(newAluno);
                }
            }
            if(indiceDis == -1){
                System.out.println("\nA disciplina não existe.\n");
            }
        } else {
            System.out.printf("\nO aluno com o numero %d nao existe.\n\n", num);
        }
    }

    public void delInscricao(int num, String sigla) {
        Aluno delAluno = null;
        int indice = -1; 
        for (Aluno searchAluno : listaAlunos) {
            if (searchAluno.getNumAluno() == num) {
                indice = listaAlunos.indexOf(searchAluno);
                delAluno = listaAlunos.get(indice);
            }
        }
        if (indice != -1) {
            int indiceDisc = -1;
            for (Disciplina searchDisciplina : listaDisciplinas) {
                if (searchDisciplina.getSigla().toLowerCase().equals(sigla.toLowerCase())) {
                    searchDisciplina.delInscrito(delAluno);
                    indiceDisc = listaDisciplinas.indexOf(searchDisciplina);
                }
            }
            if(indiceDisc == -1){
                System.out.println("\nA disciplina não existe.\n");
            }
        } else {
            System.out.printf("\nO aluno com o numero %d nao existe.\n\n", num);
        }
    }
}
