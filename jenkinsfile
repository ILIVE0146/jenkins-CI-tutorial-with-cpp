pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh 'echo Building...'
                sh 'g++ src/addition.cpp -o bin/build/add'
                sh 'g++ src/multiplication.cpp -o bin/build/mul'
                sh 'g++ src/subtraction.cpp -o bin/build/sub'
                script {
                    stash includes: 'bin/build/*', name: 'builds'
                }
            }
        }
        stage('Test') {
            steps {
                sh 'echo Running tests'
                sh 'g++ tests/client_tester.cpp - o bin/tests/tester'
                sh 'echo Testing addition microservice'
                sh 'bin/build/add 33983 &'
                sh 'bin/tests/tester 33983 10 5'
                sh 'echo Testing multiplication microservice'
                sh 'bin/build/mul 33983 &'
                sh 'bin/tests/tester 33983 10 5'
                sh 'echo Testing subtraction microservice'
                sh 'bin/build/sub 33983 &'
                sh 'bin/tests/tester 33983 10 5'
            }
        }
        stage('Publish') {
            sh 'zip -r build_Debian bin/build/*'
            archiveArtifacts artifacts: 'build_Debian.zip', fingerprint: true
            script {
                unstash 'builds'
            }
        }
    }
}