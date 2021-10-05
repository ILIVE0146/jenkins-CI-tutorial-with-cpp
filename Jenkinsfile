pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh "echo Building..."
                sh "g++ ./src/addition.cpp -o add.out"
                sh "g++ ./src/multiplication.cpp -o mul.out"
                sh "g++ ./src/subtraction.cpp -o sub.out"
                script {
                    stash includes: "*.out", name: "builds"
                }
            }
        }
        stage('Test') {
            steps {

                sh "echo Running tests"
                sh "g++ ./tests/client_tester.cpp -o tester.out"
                sh "echo Testing addition microservice"
                sh "ls"
                sh "./add.out 33983 &"
                sh "./tester.out 33983 10 5"
                sh "echo Testing multiplication microservice"
                sh "./mul.out 33983 &"
                sh "./tester.out 33983 10 5"
                sh "echo Testing subtraction microservice"
                sh "./sub.out 33983 &"
                sh "./tester.out 33983 10 5"
                sh "rm ./tester.out"
            }
        }
        stage('Archive') {
            steps {
                sh "zip -r build_Debian *.out"
                archiveArtifacts artifacts: "build_Debian.zip", fingerprint: true
                script {
                    unstash "builds"
                }
            }
        }
    }
}