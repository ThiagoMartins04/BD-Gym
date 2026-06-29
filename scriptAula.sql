CREATE SCHEMA TrabalhoBD;
USE TrabalhoBD;

CREATE TABLE Pessoa (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    cpf VARCHAR(14) NOT NULL UNIQUE,
    dataNascimento DATE NOT NULL,
    sexo ENUM('M','F'),
    telefone VARCHAR(20),
    email VARCHAR(100) UNIQUE
);

CREATE TABLE Usuario (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_pessoa INT NOT NULL UNIQUE,
    dataCadastro DATETIME DEFAULT CURRENT_TIMESTAMP,
    login VARCHAR(50) NOT NULL UNIQUE,
    senha VARCHAR(255) NOT NULL,
    FOREIGN KEY (id_pessoa) REFERENCES Pessoa(id)
);

CREATE TABLE Plano (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(50) NOT NULL,
    precoMes DECIMAL(10,2) NOT NULL,
    precoAno DECIMAL(10,2)
);

CREATE TABLE Aluno (
    id INT PRIMARY KEY,
    peso DECIMAL(5,2),
    altura DECIMAL(4,2),
    id_plano INT,
    FOREIGN KEY (id) REFERENCES Usuario(id),
    FOREIGN KEY (id_plano) REFERENCES Plano(id)
);

CREATE TABLE AlunoMensalidade (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_aluno INT NOT NULL,
    parcela INT NOT NULL,
    valor DECIMAL(10,2) NOT NULL,
    valorbaixado DECIMAL(10,2) DEFAULT 0,
    competencia DATE NOT NULL,
    FOREIGN KEY (id_aluno) REFERENCES Aluno(id)
);

CREATE TABLE Especialidade (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL UNIQUE
);

CREATE TABLE Professor (
    id INT PRIMARY KEY,
    salario DECIMAL(10,2) NOT NULL,
    id_especialidade INT,
    turno ENUM('MANHA','TARDE','NOITE'),
    FOREIGN KEY (id) REFERENCES Usuario(id),
    FOREIGN KEY (id_especialidade) REFERENCES Especialidade(id)
);

CREATE TABLE Treino (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_aluno INT NOT NULL,
    id_professor INT NOT NULL,
    dataTreino DATE NOT NULL,
    finalizado BOOLEAN DEFAULT FALSE,
    FOREIGN KEY (id_aluno) REFERENCES Aluno(id),
    FOREIGN KEY (id_professor) REFERENCES Professor(id)
);

CREATE TABLE Exercicio (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    repeticoes INT,
    series INT,
    id_especialidade INT,
    FOREIGN KEY (id_especialidade) REFERENCES Especialidade(id)
);

CREATE TABLE TreinoExercicio (
    id_treino INT,
    id_exercicio INT,
    executado BOOLEAN DEFAULT FALSE,
    PRIMARY KEY (id_treino, id_exercicio),
    FOREIGN KEY (id_treino) REFERENCES Treino(id),
    FOREIGN KEY (id_exercicio) REFERENCES Exercicio(id)
);

-- Insert planos
INSERT INTO Plano (nome, precoMes, precoAno) VALUES 
('Mensal', 150, 1800),
('Trimestral', 130, 1560),
('Semestral', 110, 1320),
('Anual', 80, 960)

-- Insert especialidade
INSERT INTO Especialidade (nome) VALUES 
('Cardio'),
('Musculacao'),
('Crossfit'),
('Calistenia'),
('Yoga'),
('Pilates'),
('Danca')

-- Insert exercicios
INSERT INTO Exercicio (nome, repeticoes, series, id_especialidade) VALUES
-- CARDIO (1)
('Corrida na esteira', 1, 1, 1),
('Bicicleta ergométrica', 1, 1, 1),
('Elíptico', 1, 1, 1),
('Pular corda', 50, 3, 1),
-- MUSCULACAO (2)
('Supino reto', 12, 4, 2),
('Agachamento livre', 10, 4, 2),
('Leg press', 12, 4, 2),
('Rosca direta', 12, 3, 2),
('Tríceps pulley', 12, 3, 2),
('Puxada na barra', 10, 4, 2),
-- CROSSFIT (3)
('Burpee', 15, 4, 3),
('Kettlebell swing', 20, 4, 3),
('Box jump', 12, 4, 3),
('Wall ball', 15, 4, 3),
-- CALISTENIA (4)
('Flexão de braço', 15, 4, 4),
('Barra fixa', 8, 4, 4),
('Abdominal', 20, 4, 4),
('Prancha', 1, 3, 4),
-- YOGA (5)
('Postura da árvore', 1, 3, 5),
('Postura do guerreiro', 1, 3, 5),
('Saudação ao sol', 5, 2, 5),
-- PILATES (6)
('The hundred', 10, 3, 6),
('Roll up', 8, 3, 6),
('Leg circles', 10, 3, 6),
-- DANCA (7)
('Aquecimento rítmico', 1, 1, 7),
('Coreografia básica', 5, 3, 7),
('Movimentos livres', 1, 2, 7);

INSERT INTO Pessoa (nome, cpf, dataNascimento, sexo, telefone, email) VALUES
('João Silva', '12345678901', '1995-03-15', 'M', '11987654321', 'joao.silva@email.com'),
('Maria Oliveira', '23456789012', '1992-07-22', 'F', '11976543210', 'maria.oliveira@email.com'),
('Carlos Souza', '34567890123', '1988-11-10', 'M', '11965432109', 'carlos.souza@email.com'),
('Ana Pereira', '45678901234', '1999-01-05', 'F', '11954321098', 'ana.pereira@email.com'),
('Lucas Santos', '56789012345', '1990-06-18', 'M', '11943210987', 'lucas.santos@email.com'),
('Juliana Costa', '67890123456', '1993-09-30', 'F', '11932109876', 'juliana.costa@email.com'),
('Rafael Almeida', '78901234567', '1987-12-12', 'M', '11921098765', 'rafael.almeida@email.com'),
('Fernanda Rocha', '89012345678', '1996-04-25', 'F', '11910987654', 'fernanda.rocha@email.com'),
('Bruno Martins', '90123456789', '1985-08-08', 'M', '11999887766', 'bruno.martins@email.com'),
('Patrícia Lima', '01234567890', '1994-02-14', 'F', '11988776655', 'patricia.lima@email.com'),
('Diego Ferreira', '11223344556', '1991-05-20', 'M', '11977665544', 'diego.ferreira@email.com'),
('Camila Gomes', '22334455667', '1998-10-11', 'F', '11966554433', 'camila.gomes@email.com'),
('Gustavo Ribeiro', '33445566778', '1989-03-03', 'M', '11955443322', 'gustavo.ribeiro@email.com'),
('Larissa Carvalho', '44556677889', '1997-07-19', 'F', '11944332211', 'larissa.carvalho@email.com'),
('Felipe Barbosa', '55667788990', '1992-12-01', 'M', '11933221100', 'felipe.barbosa@email.com'),
('Renata Teixeira', '66778899001', '1995-09-09', 'F', '11922110099', 'renata.teixeira@email.com'),
('André Moreira', '77889900112', '1986-06-27', 'M', '11911009988', 'andre.moreira@email.com'),
('Beatriz Nunes', '88990011223', '2000-01-17', 'F', '11900998877', 'beatriz.nunes@email.com'),
('Thiago Mendes', '99001122334', '1993-11-23', 'M', '11899887766', 'thiago.mendes@email.com'),
('Aline Barros', '10111213141', '1996-08-05', 'F', '11888776655', 'aline.barros@email.com');

-- Insert Usuarios
INSERT INTO Usuario (id, id_pessoa, dataCadastro, login, senha) VALUES
(1, 1, NOW(), 'joao.silva', '123456'),
(2, 2, NOW(), 'maria.oliveira', '123456'),
(3, 3, NOW(), 'carlos.souza', '123456'),
(4, 4, NOW(), 'ana.pereira', '123456'),
(5, 5, NOW(), 'lucas.santos', '123456'),
(6, 6, NOW(), 'juliana.costa', '123456'),
(7, 7, NOW(), 'rafael.almeida', '123456'),
(8, 8, NOW(), 'fernanda.rocha', '123456'),
(9, 9, NOW(), 'bruno.martins', '123456'),
(10, 10, NOW(), 'patricia.lima', '123456'),
(11, 11, NOW(), 'diego.ferreira', '123456'),
(12, 12, NOW(), 'camila.gomes', '123456'),
(13, 13, NOW(), 'gustavo.ribeiro', '123456'),
(14, 14, NOW(), 'larissa.carvalho', '123456'),
(15, 15, NOW(), 'felipe.barbosa', '123456'),
(16, 16, NOW(), 'renata.teixeira', '123456'),
(17, 17, NOW(), 'andre.moreira', '123456'),
(18, 18, NOW(), 'beatriz.nunes', '123456'),
(19, 19, NOW(), 'thiago.mendes', '123456'),
(20, 20, NOW(), 'aline.barros', '123456');

-- Insert alunos
INSERT INTO Aluno (id, peso, altura, id_plano) VALUES
(1, 72.5, 1.75, 1),  -- Mensal
(2, 60.2, 1.65, 1),  -- Mensal
(3, 85.0, 1.80, 4),  -- Anual
(4, 55.3, 1.60, 2),  -- Trimestral
(5, 90.1, 1.82, 4),  -- Anual
(6, 68.4, 1.70, 2),  -- Trimestral
(7, 77.7, 1.78, 3),  -- Semestral
(8, 59.9, 1.62, 1),  -- Mensal
(9, 88.8, 1.85, 4),  -- Anual
(10, 62.3, 1.68, 2), -- Trimestral
(11, 79.5, 1.76, 3), -- Semestral
(12, 58.0, 1.63, 1), -- Mensal
(13, 83.2, 1.79, 3), -- Semestral
(14, 61.4, 1.67, 2), -- Trimestral
(15, 87.6, 1.83, 4); -- Anual

-- Insert mensalidade dos alunos
INSERT INTO AlunoMensalidade (id_aluno, parcela, valor, valorbaixado, competencia) VALUES
(1, 1, 150, 150, '2025-01-01'),
(2, 1, 150, 150, '2025-01-01'),
(8, 1, 150, 0, '2025-01-01'),
(12,1, 150, 150, '2025-01-01'),
(4,1,130,130,'2025-01-01'),
(4,2,130,130,'2025-02-01'),
(4,3,130,0, '2025-03-01'),
(6,1,130,130,'2025-01-01'),
(6,2,130,0, '2025-02-01'),
(6,3,130,0, '2025-03-01'),
(10,1,130,130,'2025-01-01'),
(10,2,130,130,'2025-02-01'),
(10,3,130,130,'2025-03-01'),
(14,1,130,130,'2025-01-01'),
(14,2,130,0, '2025-02-01'),
(14,3,130,0, '2025-03-01'),
(7,1,110,110,'2025-01-01'),
(7,2,110,110,'2025-02-01'),
(7,3,110,110,'2025-03-01'),
(7,4,110,0, '2025-04-01'),
(7,5,110,0, '2025-05-01'),
(7,6,110,0, '2025-06-01'),
(11,1,110,110,'2025-01-01'),
(11,2,110,110,'2025-02-01'),
(11,3,110,0, '2025-03-01'),
(11,4,110,0, '2025-04-01'),
(11,5,110,0, '2025-05-01'),
(11,6,110,0, '2025-06-01'),
(13,1,110,110,'2025-01-01'),
(13,2,110,110,'2025-02-01'),
(13,3,110,110,'2025-03-01'),
(13,4,110,110,'2025-04-01'),
(13,5,110,0, '2025-05-01'),
(13,6,110,0, '2025-06-01'),
(3,1,80,80,'2025-01-01'),
(3,2,80,80,'2025-02-01'),
(3,3,80,80,'2025-03-01'),
(3,4,80,80,'2025-04-01'),
(3,5,80,80,'2025-05-01'),
(3,6,80,80,'2025-06-01'),
(3,7,80,0,'2025-07-01'),
(3,8,80,0,'2025-08-01'),
(3,9,80,0,'2025-09-01'),
(3,10,80,0,'2025-10-01'),
(3,11,80,0,'2025-11-01'),
(3,12,80,0,'2025-12-01'),
(5,1,80,80,'2025-01-01'),
(5,2,80,80,'2025-02-01'),
(5,3,80,80,'2025-03-01'),
(5,4,80,80,'2025-04-01'),
(5,5,80,0,'2025-05-01'),
(5,6,80,0,'2025-06-01'),
(5,7,80,0,'2025-07-01'),
(5,8,80,0,'2025-08-01'),
(5,9,80,0,'2025-09-01'),
(5,10,80,0,'2025-10-01'),
(5,11,80,0,'2025-11-01'),
(5,12,80,0,'2025-12-01'),
(9,1,80,80,'2025-01-01'),
(9,2,80,80,'2025-02-01'),
(9,3,80,80,'2025-03-01'),
(9,4,80,0,'2025-04-01'),
(9,5,80,0,'2025-05-01'),
(9,6,80,0,'2025-06-01'),
(9,7,80,0,'2025-07-01'),
(9,8,80,0,'2025-08-01'),
(9,9,80,0,'2025-09-01'),
(9,10,80,0,'2025-10-01'),
(9,11,80,0,'2025-11-01'),
(9,12,80,0,'2025-12-01'),
(15,1,80,80,'2025-01-01'),
(15,2,80,80,'2025-02-01'),
(15,3,80,80,'2025-03-01'),
(15,4,80,80,'2025-04-01'),
(15,5,80,80,'2025-05-01'),
(15,6,80,0,'2025-06-01'),
(15,7,80,0,'2025-07-01'),
(15,8,80,0,'2025-08-01'),
(15,9,80,0,'2025-09-01'),
(15,10,80,0,'2025-10-01'),
(15,11,80,0,'2025-11-01'),
(15,12,80,0,'2025-12-01');

-- Insert professores
INSERT INTO Professor (id, salario, id_especialidade, turno) VALUES
(16, 3500.00, 1, 'MANHA'),
(17, 4200.00, 2, 'TARDE'),
(18, 3900.00, 3, 'NOITE'),
(19, 4500.00, 1, 'MANHA'),
(20, 4000.00, 2, 'NOITE');

-- Insert em treino
INSERT INTO Treino (id, id_aluno, id_professor, dataTreino, finalizado) VALUES
(1, 1, 16, '2025-01-10', TRUE),
(2, 2, 17, '2025-01-11', TRUE),
(3, 3, 18, '2025-01-12', FALSE),
(4, 4, 19, '2025-01-13', TRUE),
(5, 5, 20, '2025-01-14', FALSE),
(6, 6, 16, '2025-01-15', TRUE),
(7, 7, 17, '2025-01-16', FALSE),
(8, 8, 18, '2025-01-17', TRUE),
(9, 9, 19, '2025-01-18', FALSE),
(10,10,20, '2025-01-19', TRUE),
(11,11,16, '2025-01-20', FALSE),
(12,12,17, '2025-01-21', TRUE),
(13,13,18, '2025-01-22', FALSE),
(14,14,19, '2025-01-23', TRUE),
(15,15,20, '2025-01-24', FALSE);

-- Insert em TreinoExercicio
INSERT INTO TreinoExercicio (id_treino, id_exercicio, executado) VALUES
-- Treino 1 (Musculação)
(1,5,TRUE),(1,6,TRUE),(1,7,TRUE),
-- Treino 2 (Musculação)
(2,8,TRUE),(2,9,TRUE),(2,10,TRUE),
-- Treino 3 (Crossfit)
(3,11,FALSE),(3,12,FALSE),(3,13,FALSE),
-- Treino 4 (Musculação)
(4,5,TRUE),(4,6,TRUE),(4,8,TRUE),
-- Treino 5 (Musculação)
(5,7,FALSE),(5,9,FALSE),(5,10,FALSE),
-- Treino 6 (Musculação)
(6,5,TRUE),(6,8,TRUE),(6,9,TRUE),
-- Treino 7 (Funcional/Crossfit)
(7,11,FALSE),(7,12,FALSE),(7,14,FALSE),
-- Treino 8 (Calistenia)
(8,15,TRUE),(8,16,TRUE),(8,17,TRUE),
-- Treino 9 (Musculação)
(9,5,FALSE),(9,6,FALSE),(9,7,FALSE),
-- Treino 10 (Musculação)
(10,8,TRUE),(10,9,TRUE),(10,10,TRUE),
-- Treino 11 (Musculação)
(11,5,FALSE),(11,6,FALSE),(11,7,FALSE),
-- Treino 12 (Musculação)
(12,8,TRUE),(12,9,TRUE),(12,10,TRUE),
-- Treino 13 (Crossfit)
(13,11,FALSE),(13,12,FALSE),(13,13,FALSE),
-- Treino 14 (Musculação)
(14,5,TRUE),(14,7,TRUE),(14,9,TRUE),
-- Treino 15 (Musculação)
(15,6,FALSE),(15,8,FALSE),(15,10,FALSE);