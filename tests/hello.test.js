import test from 'ava'
import { exec } from 'child_process'

test('should compile a simple program', async t => {
  const program = await testProgram('hello')
  console.log(program)

  t.pass()
})

const testProgram = program => execCommand(`dist/elastiq-compiler tests/fixtures/${program}.el`)


const execCommand = command => {
  console.log(`Running command: ${command}`)

  return new Promise((resolve, reject) => {
    exec(command, (err, stdout, stderr) => {
      if (err) {
        console.error(`${stdout}\n\n${stderr}\n\n`)
        return reject(err)
      }

      resolve(stdout)
    })
  })
}
