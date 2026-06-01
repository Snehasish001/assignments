public class SpecialStack extends InnerStack{
    SpecialStack(int size) {
        super(size);
    }
    
    @Override
    public void push(int item) throws StackException{
        if (!isEmpty() && peek() < item) throw new StackException("Input is greater");
        super.push(item);
    }
}
