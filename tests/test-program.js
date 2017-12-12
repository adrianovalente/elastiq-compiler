import { exec } from 'child_process'
export default function testProgram ({ program, shouldFail = false }) {
  execCommand(`dist/elastiq-compiler tests/fixtures/${program}.el`)
    .then(r => {
      if (shouldFail !== r.failed) {
        console.error(r.output)

        throw new Error(`Compilation should ${ !fail ? 'not ' : ''}fail`)
      }
    })

}

const execCommand = command => {
  // console.log(`Running command: ${command}`)

  return new Promise((resolve, reject) => {
    exec(command, (err, stdout, stderr) => {
      resolve({
        output: stdout,
        failed: !!err
      })
    })
  })
}
